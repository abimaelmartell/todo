var app = app || {};
(function(){
  app.TodoView = Backbone.View.extend({
    tagName: 'li',
    template: _.template($("#todo-template").html()),
    events: {
      'click': 'changeStatus'
    },
    render: function(){
      this.$el.html(this.template(this.model.toJSON()));
      if(this.model.get("status") == 1){
        this.$el.addClass("done");
      }
      return this;
    },
    changeStatus: function(){
      this.model.changeStatus();
    }
  });
})()
