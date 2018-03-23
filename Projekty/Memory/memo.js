var Images = [
	"img/1.png",
	"img/2.png",
	"img/3.png",
	"img/4.png",
	"img/5.png",
	"img/6.png",	
	"img/7.png",
	"img/8.png",
	"img/9.png",
	"img/10.png",
	"img/11.png",
	"img/12.png",
	"img/13.png",
	"img/14.png",
	"img/15.png",
	"img/16.png",
	"img/17.png",
	"img/18.png",
  
];

var BoxOpen = "";
var ImgOpen = "";
var ImgFound = 0;
var Length = Images.length;

function Rand(MaxValue, MinValue) {
		return Math.round(Math.random() * (MaxValue - MinValue) + MinValue);
}

function ShuffleImages() {
	var ImgThis = $("#box div:first-child");
	var ImgArr = new Array();

	var i=0;
	while(ImgThis.attr("id") != undefined) {
		ImgArr[i] = $("#" + ImgThis.attr("id") + " img").attr("src");
		ImgThis = ImgThis.next();
		i++;	
		}
	
	ImgThis = $("#box div:first-child");

	while(ImgArr != "") {		
		var r = Rand(ImgArr.length-1,0);
		$("#" + ImgThis.attr("id") + " img").attr("src", ImgArr[r]);
		ImgArr.splice(r, 1);
		ImgThis = ImgThis.next();
	}
}

function Open() {
	var Id = $(this).attr("id");
	
	if ($("#" + Id + " img").is(":hidden")) {
		$("#" + Id + " img").fadeIn(500);
		if (ImgOpen == "") {
			ImgOpen = $("#" + Id + " img").attr("src");
			BoxOpen = Id;
			$("#box div").bind("click", Open);
		} else {
			if (ImgOpen == $("#" + Id + " img").attr("src")) {
				setTimeout(function() {
				$("#" + Id + " img").parent().css("visibility", "hidden");
				$("#" + BoxOpen + " img").parent().css("visibility", "hidden");
				$("#all").append("<img src=" + ImgOpen + " />");
				ImgFound++;
				BoxOpen = "";
				ImgOpen = "";
				if (ImgFound == Length){
					alert("Wygrałeś! Ok dla nowej gry!");
					Reset();
					}
			}, 800); 
				
			} else {
				setTimeout(function() {
					$("#" + Id + " img").fadeOut(300);
					$("#" + BoxOpen + " img").fadeOut(300);
					BoxOpen = "";
					ImgOpen = "";
					$("#box div").bind("click", Open);

				}, 700);
			}
			
		}
		

	}
	
}
function Reset(){
	ShuffleImages();
	$("#box div img").hide();
	$("#all img").hide();
	$("#box div").css("visibility", "visible");
	ImgFound = 0;
	
	return false;
}
function cheatsenabletrue(){
	$("#box div img").fadeIn('fast');
	setTimeout(function() {
	$("#box div img").fadeOut('fast');
	}, 1000);
	return false;
}

$(function() {

	for (var y = 1; y < 3 ; y++) {
		$.each(Images, function(i, val) {
			$("#box").append("<div id=card" + y + "_" + i + "><img src=" + val + " />");
		});
	}
	$("#box div").click(Open);
	ShuffleImages();
});	