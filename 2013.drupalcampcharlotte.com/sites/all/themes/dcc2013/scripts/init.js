(function ($) {
	$(document).ready(function() {
		setupInfield();
		setupScrollspy();
		highlightNav();
		if(isiPhone()){
			setupHideSearchBar();
		}
		//setupFontResize();
	});

	function setupInfield() {
		$(".infield").inFieldLabels();
	}

	function setupScrollspy() {
		$('.second-main-nav').scrollspy();
		$('[data-spy="scroll"]').each(function () {
			var $spy = $(this).scrollspy('refresh');
		});
	}

	function setupFontResize() {
		causeRepaintsOn = $(".header h2, .email h2");

		$(window).resize(function() {
			causeRepaintsOn.css("z-index", 1);
		});
	}

	function setupHideSearchBar() {
		// When ready...
		window.addEventListener("load",function() {
			// Set a timeout...
			setTimeout(function(){
				// Hide the address bar!
				window.scrollTo(0, 1);
			}, 0);
		});
	}

	function isiPhone(){
		return (
		//Detect iPhone
		//var isiPad = navigator.userAgent.match(/iPad/i) != null;
			(navigator.platform.indexOf("iPhone") !== -1) ||
			//Detect iPod
			(navigator.platform.indexOf("iPad") !== -1)
		);
	}


	function highlightNav(){

		var sections = $(".sections");
		var navigation_links = $(".sticky_nav li a");

		sections.waypoint({
			handler: function(event, direction) {

				var active_section;
				active_section = $(this);
				if (direction === "up") { active_section = active_section.prev(); }

				var active_link = $('.sticky_nav li a[href="#' + active_section.attr("id") + '"]');
				navigation_links.removeClass("active");
				active_link.addClass("active");

			},
			offset: '25%'
		});

	}

	$(window).load(function() {
		/* get window size */
		var windowSize = $(window);

		windowSize.scroll(function() {

			/* Get distance from the top */
			var top = windowSize.scrollTop();

			/* If distance from the top is bigger than 50px, than change the top valeu from -50px to 0px  (make it appear)*/
			if(top > 625) {
				$(".second-main-nav").css("top","0");
			}

			/* If distance from the top is equals 0, than change the top valeu from 0 to -50px (hide it)*/
			if(top < 625) {
				$(".second-main-nav").css("top","-135px");
			}

			/* Show the top value on the p element within the .container */
			$('.container p').text(top);
		});
	});
}(jQuery));
