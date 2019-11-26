const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<head>
  <title>H&ouml;henmesser</title>
   <script src = "Chart.min.js"></script>
  <style>
  canvas{
    -moz-user-select: none;
    -webkit-user-select: none;
    -ms-user-select: none;
  }

  // Tabelle
  #dataTable {
    font-family: "Verdana", Arial, Helvetica, sans-serif;
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
    </div>
    <div class="chart-container" style="position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>
<div>
  <table id="dataTable">
    <tr><th>Zeit</th><th>H&ouml;he</th><th>Geschwindigkeit</th><th>Beschleunigung</th></tr>
  </table>
</div>

<script>
  var data = [];
  var speed = [];
  var acceleration = [];
  var time = "";

  let graph;

  function addGraph()
  {
    var ctx = document.getElementById("Chart").getContext('2d');
    graph = new Chart(ctx, {
      type: 'line',
        data: {
        labels: [time],  // X-Achse 
        datasets: [
        {
          label: "H\u00f6he in m",
          fill: false,  
          backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
          borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
          data: null, // Wenn es noch keine Daten gibt wird 'null' angezeigt
        },
        {
          label: "Geschwindigkeit in m/s",
          fill: false,  
          backgroundColor: 'rgba(0, 140, 192, 1)',
          borderColor: 'rgba(0, 140, 192, 1)', 
          data: null, 
          hidden: true,
          },
          {
          label: "Beschleunigung in m/s\u00B2",
          fill: false,  
          backgroundColor: 'rgba(38, 223, 59, 1)', 
          borderColor: 'rgba(38, 223, 59, 1)', 
          data: null,
          hidden: true,
        }],
        },
        options: {
          title: {
            display: false,
            text: "H\u00f6he"
          },
          maintainAspectRatio: false,
          elements: {
            line: {
              tension: 0.0 // Rundung des Graphen
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

  // Graphen nach erhalt neuer Daten aktualisieren
  function updateGraph() {
    graph.data.labels.push(time);
    graph.data.datasets[0].data.push(data);
    graph.data.datasets[1].data.push(speed);
    graph.data.datasets[2].data.push(acceleration);
    graph.update();
  }

  // Beim Starten der Seite Graphen anzeigen
  window.onload = function() {
    addGraph();
  };

  // Update-Geschwindigkeit (429 ms)
  setInterval(function() {
    getData();
  }, 100); 

  // Daten unter /readData abrufen
  function getData() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
        var response = this.responseText.split(";"); // Erstellt ein array aus den Teilen des response-strings (';' ist das Trennzeichen)
        time = response[0]; // Zeit hat den ersten Index...
        data = response[1]; // ...und die Höhe den zweiten
        speed = response[2];
        acceleration = response[3];
        updateGraph();
        var table = document.getElementById("dataTable");
        var row = table.insertRow(1); //Add after headings
        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);
        var cell3 = row.insertCell(2);
        var cell4 = row.insertCell(3);
        cell1.innerHTML = time;
        cell2.innerHTML = data;
        cell3.innerHTML = speed;
        cell4.innerHTML = acceleration;
      }
    };
    xhttp.open("GET", "readData", true);
    xhttp.send();
  }
</script>
</body>

</html>

)=====";
