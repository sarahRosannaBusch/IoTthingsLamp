var deviceID = "3e0031000847343133353336"; //change these to your device's
var accessToken = "4ed978c8d44ee74e0da0a2e08db5dcd401ce9958"; //eventually these values will be obtained from a user form

//this function is based on https://community.particle.io/t/reading-spark-variables-with-your-own-html-file/4148
//this seems to be the easiest way to get the data since Particle gives it in JSON format
function readPhotoresistor()
{
  document.getElementById('light').innerHTML = "Waiting for result...";

  requestURL = "https://api.particle.io/v1/devices/" + deviceID + "/A0value?access_token=" + accessToken;
  $.getJSON(requestURL, function(json) {
                 document.getElementById("light").innerHTML = "Analog Value: " + json.result;
                 });
}

function lampOn()
{
  //Create an XMLHttpRequest Object with AJAX for POSTs
  var xhr;
    try { xhr = new XMLHttpRequest(); }
    catch(e) { xhr = new ActiveXObject('Microsoft.XMLHTTP'); } //for old versions of IE
  xhr.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("lampStatus").innerHTML = this.responseText;
    }
  };
  xhr.open("POST", "https://api.particle.io/v1/devices/" + deviceID + "/lampOn?access_token=" + accessToken, true);
  xhr.send();
}

function lampOff()
{
  //Create an XMLHttpRequest Object with AJAX for POSTs
  var xhr;
    try { xhr = new XMLHttpRequest(); }
    catch(e) { xhr = new ActiveXObject('Microsoft.XMLHTTP'); } //for old versions of IE
  xhr.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("lampStatus").innerHTML = this.responseText;
    }
  };
  xhr.open("POST", "https://api.particle.io/v1/devices/" + deviceID + "/lampOff?access_token=" + accessToken, true);
  xhr.send();
}
