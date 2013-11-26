var app = app || {};
(function(){
  app.TodoView = Backbone.View.extend({
    tagName: 'li',
    template: _.template($("#todo-template").html()),
    events: {
      'click .check': 'changeStatus',
      'click span': 'showEditInput',
      'keypress input': 'updateText'
    },
    initialize: function(){
      this.listenTo(this.model, 'change', this.render);
    },
    render: function(){
      this.$el.html(this.template(this.model.toJSON()));
      if(this.model.get("status") == 1){
        this.$el.addClass("done");
      }else{
        this.$el.removeClass("done");
      }
      return this;
    },
    changeStatus: function(event){
      this.model.changeStatus();
    },
    showEditInput: function(event){
      this.$el.find("span").hide();
      this.$el.find("input").show().focus();
    },
    updateText: function(event){
      var $input = this.$el.find('input'),
          text = $input.val().trim();
      if(event.which != 13 || text == "")
        return;
      this.model.save({ text: text });
      $input.hide();
      this.$el.find("span").show();
    }
  });
})()
