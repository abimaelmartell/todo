var app = app || {};
(function() {

    app.Todo = Backbone.Model.extend({
        urlRoot: '/todos',

        defaults: {
            text: '',
            status: ''
        },

        changeStatus: function() {
            var newStatus = this.get("status") == 0 ? 1 : 0;
            this.save({ status: newStatus });
        }
    });

    app.TodoCollection = Backbone.Collection.extend({
        model: app.Todo,
        url: "/todos",

        completed: function() {
            return this.where({ status: 1 });
        }
    });

    app.Todos = new app.TodoCollection();

    app.TodoView = Backbone.View.extend({
        tagName: 'li',
        template: _.template($("#todo-template").html()),

        events: {
            'click .check': 'changeStatus',
            'click span': 'showEditInput',
            'keypress input': 'updateText'
        },

        initialize: function() {
            this.listenTo(this.model, 'change', this.render);
            this.listenTo(this.model, 'destroy', this.remove);
        },

        render: function() {
            this.$el.html(this.template(this.model.toJSON()));

            if (this.model.get("status") == 1) {
                this.$el.addClass("done");
            } else {
                this.$el.removeClass("done");
            }

            return this;
        },

        changeStatus: function(event) {
            this.model.changeStatus();
        },

        showEditInput: function(event) {
            this.$el.find("span").hide();
            this.$el.find("input").show().focus();
        },

        updateText: function(event) {
            var $input = this.$el.find('input')
              , text = $input.val().trim();

            if (event.which != 13 || text == "") {
                return;
            }

            this.model.save({ text: text });
            $input.hide();
            this.$el.find("span").show();
        }
    });

    app.AppView = Backbone.View.extend({
        el: '.container',

        events: {
            'keypress #todo-text': 'createTodo',
            'click #delete-completed': 'deleteCompleted'
        },

        initialize: function() {
            this.listenTo(app.Todos, 'add', this.addOne);
            this.listenTo(app.Todos, 'all', this.render);
            this.listenTo(app.Todos, 'reset', this.addAll);

            app.Todos.fetch({ reset: true });
        },

        addOne: function(todo) {
            var todoView = new app.TodoView({ model: todo });
            $("ul.todos").prepend(todoView.render().el);
        },

        addAll: function() {
            $("ul.todos").html();
            app.Todos.each(this.addOne, this);
        },

        createTodo: function(event) {
            if (event.which != 13) {
                return;
            } else {
                event.preventDefault();
            }

            var text = $("#todo-text").val().trim();

            if (text == "") {
                return;
            }

            app.Todos.create({ text: text });

            $("#todo-text").val('');
        },

        deleteCompleted: function() {
            _.invoke(app.Todos.completed(), 'destroy');
        }
    });

    new app.AppView();
})()
