var app = app || {};
(function(){
  app.AppView = Backbone.View.extend({
    el: '.container',
    events: {
      'keypress #todo-text': 'createTodo'
    },
    initialize: function(){
      this.listenTo(app.Todos, 'add', this.addOne);
      app.Todos.fetch({reset: true});
    },
    addOne: function(todo){
    },
    createTodo: function(event){
      if(event.which != 13){
        return;
      }else{
        event.preventDefault();
      }
      app.Todos.create({ text: $("#todo-text").val() });
    }
  });
})();
