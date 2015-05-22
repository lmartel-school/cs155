# Warmup [tested]

Enabled (default) CSP, which prevents the execution of inline scripts and disables loading scripts from sources other than 'self'. This also disables the starter code's framebusting protection and wonky account balance animation, but both of those things must be replaced in other defenses (B+ and D, respectively) anyway.

Changed application_controller.rb


# Attack A: Cookie Forgery [description only]

The problem is that bitbar doesn't store any cookie information on the server, so it can't detect manufactured cookies. Keep a session database that stores the cookies of logged-in users, and verify that the stored cookie matches the user's cookie on each request.

Changed nothing


# Attack B [tested]

Added a hidden CSRF token to the transfer form. When the form page is requested, the server generates a random token to use for CSRF, and stores it in the session as well as in the hidden form field. On form submission, it ensures that these fields are present and match.

Note that this scheme is vulnerable to cookie forgery like in Attack A, so this defense assumes that the defense described in A is implemented.

Changed user_controller.rb, users/transfer_form.html.erb


# Attack B+ [tested]

Added improved framebusting code courtesy of Prof. Boneh et al's paper at https://crypto.stanford.edu/~dabo/pubs/papers/framebust.pdf. Put the css directly into the layout, but put the js in a new file (assets/javascripts/application.js) because of the new CSP.

The framebusting code styles the website (with css) to be blank by default, then reveals the page if the frame is top. Otherwise, attempts to bust out of frame.

Changed layouts/application.html.erb, added application.js


# Attack C SQL Injection [tested]

Changed the ActiveRecord destroy_all call to use query-builder method `where(hash)` instead of raw SQL strings.

Changed user_controller.rb


# Attack D Profile Worm [tested]

Disabled inline and foreign JS with CSP, and replaced the two evals with more sensible code. The ERB template renders the bitbar total into a data attribute, then the JS uses parseInt to safely retrieve it. In addition, passing a string to setTimeout was replaced with passing an anonymous function. Finally, the tag containing the bitbars value is now *before* the profile in the document, so even if the user makes a tag with the same ID, getElementById will find ours. (Note: all this could do would ruin the display/animation, but might as well prevent this too.)

Changed profile.html.erb, added profile.js


# Attack E [tested]

We prevent funny business after a login error by properly quoting the value attribute, and html-escaping the input using the rails helper `h` method for good measure.

Changed login_form.html.erb
