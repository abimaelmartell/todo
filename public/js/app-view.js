var app = app || {};
(function(){
  app.AppView = Backbone.View.extend({
    el: '.container',
    events: {
      'keypress #todo-text': 'createTodo'
    },
    initialize: function(){
      this.listenTo(app.Todos, 'add', this.addOne);
      this.listenTo(app.Todos, 'all', this.render);
      this.listenTo(app.Todos, 'reset', this.addAll);

      app.Todos.fetch({reset: true});
    },
    render: function(){
    },
    addOne: function(todo){
      var todoView = new app.TodoView({ model: todo });
      $("ul.todos").prepend(todoView.render().el);
    },
    addAll: function(){
      $("ul.todos").html();
      app.Todos.each(this.addOne, this);
    },
    createTodo: function(event){
      if(event.which != 13){
        return;
      }else{
        event.preventDefault();
      }
      var text = $("#todo-text").val().trim();
      if(text == "")
        return;
      app.Todos.create({ text: text });
      $("#todo-text").val('');
    }
  });
})();
