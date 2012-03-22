$(document).ready(function() {
  // Remove the log-in link from logged in users
  $("body.logged-in a.user-login-link").remove();

  // Removes the register link for users who are already registered for the
  // camp.
  $('body.registered').find('.register-link').remove();
});

