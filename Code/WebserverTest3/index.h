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
    <p>Real Time Data Logging with Graphs on ESP8266</p></div>
    <div class="chart-container" style="position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <table id="dataTable">
    <tr><th>Zeit</th><th>H&ouml;he</th></tr>
  </table>
</div>

<script>
  var data = [];
  var time = "";

  let graph;

  function addGraph()
  {
    var ctx = document.getElementById("Chart").getContext('2d');
    graph = new Chart(ctx, {
      type: 'line',
        data: {
        labels: [time],  //Bottom Labeling
        datasets: [{
          label: "H\u00f6he",
          fill: false,  //Try with true
          backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
          borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
          data: null, // Wenn es noch keine Daten gibt wird 'null' angezeigt
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

  function updateGraph() {
    graph.data.labels.push(time);
    graph.data.datasets.forEach((dataset) => {
        dataset.data.push(data);
    });
    graph.update();
  }

  //On Page load show graphs
  window.onload = function() {
    addGraph();
  };

  //Ajax script to get ADC voltage at every 5 Seconds 
  //Read This tutorial https://circuits4you.com/2018/02/04/esp8266-ajax-update-part-of-web-page-without-refreshing/

  setInterval(function() {
    getData();
  }, 333); // 333ms update rate


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
        var response = this.responseText.split(";"); // Erstellt ein array aus den Teilen des response-strings (';' ist das Trennzeichen)
        time = response[0]; // Zeit hat den ersten Index...
        data = response[1]; // ...und die Höhe den zweiten
        updateGraph();
        var table = document.getElementById("dataTable");
        var row = table.insertRow(1); //Add after headings
        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);
        cell1.innerHTML = time;
        cell2.innerHTML = data;
      }
    };
    xhttp.open("GET", "getData", true);  //Handle readADC server on ESP8266
    xhttp.send();
  }
</script>
</body>

</html>

)=====";
