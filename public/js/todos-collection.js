var app = app || {};
(function(){
  var Todos = Backbone.Collection.extend({
    model: app.Todo,
    url: "/todos"
  });

  app.Todos = new Todos();
})()
