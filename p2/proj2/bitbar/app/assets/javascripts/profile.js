var disp = document.getElementById("bitbar_display");
var total = parseInt(disp.dataset.bitbars) || 0
function showBitbars(bitbars) {
  disp.innerHTML = bitbars + " bitbars";
  if (bitbars < total) {
      setTimeout(function(){
	  showBitbars(bitbars + 1);
      }, 20);
  }
}
if (total > 0) showBitbars(0);  // count up to total
