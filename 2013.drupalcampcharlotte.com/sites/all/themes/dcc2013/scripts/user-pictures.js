(function ($) {

  Drupal.behaviors.dccUserPictures = {
    attach: function (context, settings) {
      
      $('.view-dcc-2013-attendees .views-row', context).hover(          
        function () {
          $('.views-field-nothing', this).fadeIn();
          $('.views-field-name', this).fadeIn();
          $('.views-field-field-profile-twitter-link', this).fadeIn();
          $('.views-field-field-profile-app-net-link', this).fadeIn();
        },
        function () {
          $('.views-field-nothing', this).fadeOut();
          $('.views-field-name', this).fadeOut();
          $('.views-field-field-profile-twitter-link', this).fadeOut();
          $('.views-field-field-profile-app-net-link', this).fadeOut();
        }          
      );
      
      $('.view-dcc-2013-attendees .views-field-name').hide();
      $('.view-dcc-2013-attendees .views-field-field-profile-twitter-link').hide();
      $('.view-dcc-2013-attendees .views-field-field-profile-app-net-link').hide();
      
    }
  
  };
  
}(jQuery));