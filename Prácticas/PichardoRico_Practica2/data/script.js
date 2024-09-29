function toggleCheckbox(element) {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/update?output=" + element.id + "&state=" + (element.checked ? "1" : "0"), true);
      xhr.send(); 
    }


setInterval(function() {
      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/sensorData", true);
      xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
          var sensorData = xhr.responseText.split(',');
          document.getElementById('potValue').innerText = sensorData[0];
          document.getElementById('photoValue').innerText = sensorData[1];
        }
      };
      xhr.send();
    }, 1000);


function updateSliderPWM(element) {
      var sliderValue = element.value;
      if (element.id === "4") {
        document.getElementById("textSliderValue").innerHTML = sliderValue;
      } 

      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/slider?value=" + sliderValue, true);
      xhr.send();
    }


function updateSliderPWM2(element) {
      var sliderValue2 = element.value;
      if (element.id === "5") {
        document.getElementById("textSliderValue5").innerHTML = sliderValue2;
      } 

      var xhr = new XMLHttpRequest();
      xhr.open("GET", "/slider2?value5=" + sliderValue2, true);
      xhr.send();
    }