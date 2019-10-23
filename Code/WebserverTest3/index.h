const char MAIN_page[] PROGMEM = R"=====(

<!doctype html>
<html>

<head>
  <title>H&ouml;henmesser</title>

  <script src = "https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.3/Chart.min.js"></script>  
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }

  /* Data Table Styling */
  #dataTable {
    font-family: "Trebuchet MS", Arial, Helvetica, sans-serif;
    border-collapse: collapse;
    width: 100%;
  }

  #dataTable td, #dataTable th {
    border: 1px solid #ddd;
    padding: 8px;
  }

  #dataTable tr:nth-child(even){background-color: #f2f2f2;}

  #dataTable tr:hover {background-color: #ddd;}

  #dataTable th {
    padding-top: 12px;
    padding-bottom: 12px;
    text-align: left;
    background-color: #4CAF50;
    color: white;
  }
  </style>
</head>

<body>
    <div style="text-align:center;">
    <h1 style="font-family:verdana;color:#999999">H&ouml;henmesser</h1>
      <br>Real Time Data Logging with Graphs on ESP8266</div>
    <div class="chart-container" style="position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <table id="dataTable">
    <tr><th>Time</th><th>Hoehe</th></tr>
  </table>
</div>
<br>
<br>  

<script>
var data = [];
  var time = "";
  var timeStamp = time;

  var graph;

  function addGraph()
  {
    var ctx = document.getElementById("Chart").getContext('2d');
    graph = new Chart(ctx, {
      type: 'line',
        data: {
        labels: [timeStamp],  //Bottom Labeling
        datasets: [{
          label: "Hoehe",
          fill: false,  //Try with true
          backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
          borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
          data: null,
        }],
        },
        options: {
          title: {
            display: true,
            text: "Hoehe"
          },
          maintainAspectRatio: false,
          elements: {
            line: {
              tension: 0.5 //Smoothening (Curved) of data lines
            }
          },
          scales: {
            yAxes: [{
              ticks: {
                beginAtZero:true
              }
            }]
        }
      }
    })
  }

  function updateGraph(data) {
    graph.data.labels.push(timeStamp);
    graph.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    graph.update();
  }

  //On Page load show graphs
  window.onload = function() {
    console.log(new Date().toLocaleTimeString());
    addGraph(5,10,4,58);
  };
  
  //Ajax script to get ADC voltage at every 5 Seconds 
  //Read This tutorial https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/
  
  setInterval(function() {
    // Call a function repetatively with 5 Second interval
    getData();
  }, 333); //5000mSeconds update rate
  

  function showGraph(data) {
    graph.data.labels.push(timeStamp);
    graph.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    graph.update();
  }

  function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        data = this.responseText; 
        updateGraph(data);
        var table = document.getElementById("dataTable");
        var row = table.insertRow(1); //Add after headings
        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);
        cell1.innerHTML = time;
        cell2.innerHTML = data;
      }
    };
    xhttp.open("GET", "index.php", true);  //Handle readADC server on ESP8266
    xhttp.send();
  }
  
</script>
</body>

</html>

)=====";
