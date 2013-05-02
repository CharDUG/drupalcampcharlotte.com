(function ($) {
  if($('body').hasClass('html')) {

    var $filter = $('#navigation');
    var $filterSpacer = $('<div />', {
      "class": "filter-drop-spacer",
      "height": $filter.outerHeight()
    });

    if ($filter.size())
    {
      $(window).scroll(function ()
      {
        if (!$filter.hasClass('fix') && $(window).scrollTop() > $filter.offset().top)
        {
          $filter.before($filterSpacer);
          $filter.addClass("fix");
        }
        else if ($filter.hasClass('fix')  && $(window).scrollTop() < $filterSpacer.offset().top)
        {
          $filter.removeClass("fix");
          $filterSpacer.remove();
        }
      });
    }
  }
}(jQuery));