var app = app || {};
(function(){
  var Todos = Backbone.Collection.extend({
    model: app.Todo,
    url: "/todos",
    completed: function(){
      return this.where({status: 1});
    }
  });

  app.Todos = new Todos();
})()
