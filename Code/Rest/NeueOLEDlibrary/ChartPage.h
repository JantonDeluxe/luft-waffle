const char ChartPage[] = R"=====(


<!DOCTYPE html>
<html>

<head>
    <title>Chart - H&ouml;henmesser</title>
    <script src="Chart.min.js"></script>
    <style>


        ul {
            list-style-type: none;
            box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
            margin: 0;
            padding: 0;
            overflow: hidden;
            background-color: #333;
            position: fixed;
            top: 0;
            width: 100%;
        }
        
        li {
            float: left;
        }
        
        li a {
            display: block;
            color: white;
            text-align: center;
            padding: 14px 16px;
            text-decoration: none;
            font-family: verdana;
        }
        
        li a:hover:not(.active) {
            background-color: #111;
        }
        
        .active {
            background-color: #4CAF50;
        }
        
        canvas {
            -moz-user-select: none;
            -webkit-user-select: none;
            -ms-user-select: none;
        }


        .button {
            background-color: #4CAF50;
            box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
            border: none;
            color: white;
            padding: 16px 32px;
            width: 150px;
            text-align: center;
            text-decoration: none;
            font-size: 16px;
            margin: 4px 2px;
            -webkit-transition-duration: 0.4s;
            transition-duration: 0.4s;
            cursor: pointer;
        }

         .button2 {
            border-radius: 8px;
            background-color: #f44336;
            color: white;
            border: 2px solid #f44336;
        }
        
        .button2:hover {
            border-radius: 8px;
            background-color: white;
            color: black;
            border: 2px solid #f44336;
        }

        .floated {
             float:left;
             margin-right:15px;
        }

        .box {
            height: 65px;
            width: 175px;
            line-height: 65px;  
            box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
            background-color: #4CAF50;
            color: white;
            text-align: center;
            vertical-align: baseline;
        }
        
        
    </style>
    
</head>

<body>
    <ul>
        <li><a href="/">Home</a></li>
        <li><a class="active" href="/chart">Vorschau</a></li>
        <li style="float:right"><a href="/about">About</a></li>
    </ul>

    <div style="text-align:left;">
        <h1 style="font-family:verdana;color:white">I bims 1 Platzhalter! Ohne mich geht nix ;-)</h1>
    </div>
    
    <div class="chart-container" style="position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>

    <br>

     <div style="font-family:verdana;text-align:left;padding-top:10px">
      <div class="box floated">
      Max.     <b style="font-size:150%;"><span id="highest">0</span> m</b>
      </div>
  
      <div class="box floated">
      Temp.     <b style="font-size:150%;"><span id="temp">0</span> C</b>
      </div>
  
      <div class="box floated">
      Timer     <b style="font-size:150%;"><span id="timer">0</span></b>
      </div>
    </div>

     </div>
    <br>
    <form action="/stopp" class="inline">
      <button class="button button2">Stopp</button>
    </form>

    <table id="dataTable" class="table">
        <thead>
            <tr>
                <th>Hoehe</th>
                <th>Zeit</th>
            </tr>
        </thead>
    </table>

    <button id="btnExportToCsv" type="button" class="button">Export to CSV</button>

    <script>
        const dataTable = document.getElementById("dataTable");
        const btnExportToCsv = document.getElementById("btnExportToCsv");

        btnExportToCsv.addEventListener("click", () => {
            const exporter = new TableCSVExporter(dataTable);
            const csvOutput = exporter.convertToCSV();
            const csvBlob = new Blob([csvOutput], { type: "text/csv" });
            const blobUrl = URL.createObjectURL(csvBlob);
            const anchorElement = document.createElement("a");

            anchorElement.href = blobUrl;
            anchorElement.download = "table-export.csv";
            anchorElement.click();

            setTimeout(() => {
                URL.revokeObjectURL(blobUrl);
            }, 500);
        });
    </script>

    
    <script>
        var data = [];
        var speed = [];
        var acceleration = [];
        var temperature = [];
        var time = "";
        var timer = 1;        

        let graph;

        function addGraph() {
            var ctx = document.getElementById("Chart").getContext('2d');
            graph = new Chart(ctx, {
                type: 'line',
                data: {
                    labels: [time], //Bottom Labeling
                    datasets: [{
                        label: "H\u00f6he in m",
                        fill: false,
                        backgroundColor: 'rgba( 243, 156, 18 , 1)', //Dot marker color
                        borderColor: 'rgba( 243, 156, 18 , 1)', //Graph Line Color
                        data: null, // Wenn es noch keine Daten gibt wird 'null' angezeigt
                    }, {
                        label: "Geschwindigkeit in m/s",
                        fill: false,
                        backgroundColor: 'rgba(0, 140, 192, 1)',
                        borderColor: 'rgba(0, 140, 192, 1)',
                        data: null,
                        hidden: true,
                    }, {
                        label: "Beschleunigung in m/s^2",
                        fill: false,
                        backgroundColor: 'rgba(76, 175, 80, 0.8)',
                        borderColor: 'rgba(76, 175, 80, 0.8)',
                        data: null,
                        hidden: true,
                    }, {
                        label: "Temperatur in Grad C",
                        fill: false,
                        backgroundColor: 'rgba(204, 51, 0, 0,8)',
                        borderColor: 'rgba(204, 51, 0, 0,8)',
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
                            tension: 0.2 //Smoothening (Curved) of data lines
                        }
                    },
                    scales: {
                        yAxes: [{
                            ticks: {
                                beginAtZero: true
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
            graph.data.datasets[3].data.push(temperature);
            graph.update();
        }

        //Beim Starten der Seite Graphen anzeigen
        window.onload = function() {
            addGraph();
        };

        // Update-Geschwindigkeit (115 ms)
        setInterval(function() {
            getData();
            // Beenden einer Messuung
            if (timer == 0) {
              window.location.replace("stopp");
              }
        }, 115);

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
                    temperature = response[5];
                    timer = response[6];
                    document.getElementById("highest").innerHTML = response[4];
                    document.getElementById("temp").innerHTML = response[5];
                    document.getElementById("timer").innerHTML = response[6];
                    
                    var table = document.getElementById("dataTable");
                    var row = table.insertRow(1); //Add after headings
                    var cell1 = row.insertCell(0);
                    var cell2 = row.insertCell(1);
                    cell1.innerHTML = time;
                    cell2.innerHTML = data;
        
                    updateGraph();
                }
            };
            xhttp.open("GET", "readData", true);
            xhttp.send();

            }
       
    </script>


</body>

</html>

)=====";
