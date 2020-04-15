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
            background-color: #14264f;
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
            background-color: #183754;
        }
        
        .active {
            background-color: #f39c12;
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

        .button3 {
            border-radius: 8px;
            display: inline-block;
            margin-right: 5px;
            background-color: #0080ff;
            color: white;
            border: 2px solid #0080ff;
        }
        
        .button3:hover {
            border-radius: 8px;
            display: inline-block;
            margin-right: 5px;
            background-color: white;
            color: black;
            border: 2px solid #0080ff;
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

        .box1{
          background-color: #f39c12;
        }
        
        .box2{
          background-color: grey;
        }
        
        .box3{
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
      <div class="box box1 floated">
      Max.     <b style="font-size:150%;"><span id="highest">0</span> m</b>
      </div>

      <div class="box box2 floated">
      Temp.     <b style="font-size:150%;"><span id="temp">0</span> C</b>
      </div>
  
      <div class="box floated">
      Timer     <b style="font-size:150%;"><span id="timer">0</span></b>
      </div>
    </div>
    <br>
    <br>
    <br>
    <br>
    <br>

    <button id="btnExportToCsv" type="button" class="button button3 floated">CSV-Export</button>

    <form action="/stopp" class="inline">
      <button class="button button2 floated">Stopp</button>
    </form>

    <table id="dataTable" class="table"  style="display: none">
        <thead>
            <tr>
                <th>Zeit</th>
                <th>Hoehe</th>
                <th>Geschwindigkeit</th>
                <th>Beschleunigung</th>
            </tr>
        </thead>
    </table>

    
    <script>
    
        // Variablen
        var height = [];
        var speed = [];
        var acceleration = [];
        var temperature = [];
        var time = "";
        var timer = 1;
        
        const dataTable = document.getElementById("dataTable");
        const btnExportToCsv = document.getElementById("btnExportToCsv");
        
        
        // Update-Geschwindigkeit
        setInterval(function() {
            getData();
            // Beenden einer Messuung
            if (timer == 0) {
                window.location.replace("stopp");
                timer = 1;
            }
        }, 115);   // Alle 115 Millisekunden (Dauer eines Messzyklus)
        
        
        // Daten unter abrufen
        function getData() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    var response = this.responseText.split(";"); // Erstellt ein array aus den Teilen des response-strings (';' ist das Trennzeichen)
                    time = response[0]; // Zeit hat den ersten Index...
                    height = response[1]; // ...und die Höhe den zweiten
                    speed = response[2];
                    acceleration = response[3];
                    temperature = response[5];
                    timer = response[6];
                    document.getElementById("highest").innerHTML = response[4];
                    document.getElementById("temp").innerHTML = response[5];
                    document.getElementById("timer").innerHTML = response[6];

                    updateGraph();
        
                    var table = document.getElementById("dataTable");
                    var row = table.insertRow(1);
                    var cell1 = row.insertCell(0);
                    var cell2 = row.insertCell(1);
                    var cell3 = row.insertCell(2);
                    var cell4 = row.insertCell(3);
                    cell1.innerHTML = time;
                    cell2.innerHTML = height;
                    cell3.innerHTML = speed;
                    cell4.innerHTML = acceleration;
                    
                   
                }
            };
            xhttp.open("GET", "readData", true);
            xhttp.send();
        
        }
        
        // Graphen-Darstellung
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
                        label: "Beschleunigung in m/s^2;",
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
            graph.data.datasets[0].data.push(height);
            graph.data.datasets[1].data.push(speed);
            graph.data.datasets[2].data.push(acceleration);
            graph.data.datasets[3].data.push(temperature);
            graph.update();
        }
        
        //Beim Starten der Seite Graphen anzeigen
        window.onload = function() {
            addGraph();
        };
        
        
        
        // CSV-Erstellung
        btnExportToCsv.addEventListener("click", () => {
            const exporter = new TableCSVExporter(dataTable);
            const csvOutput = exporter.convertToCSV();
            const csvBlob = new Blob([csvOutput], {
                type: "text/csv"
            });
            const blobUrl = URL.createObjectURL(csvBlob);
            const anchorElement = document.createElement("a");

        
            anchorElement.href = blobUrl;
            anchorElement.download = "table-export.csv";
            anchorElement.click();
        
            setTimeout(() => {
                URL.revokeObjectURL(blobUrl);
            }, 500);
        });
        
        class TableCSVExporter {
          
            constructor(table, includeHeaders = true) {
                this.table = table;
                this.rows = Array.from(table.querySelectorAll("tr"));
            }
        
            convertToCSV() {
                const lines = [];
                const numCols = 4;
        
                for (const row of this.rows) {
                    let line = "";
        
                    for (let i = 0; i < numCols; i++) {
                        if (row.children[i] !== undefined) {
                            line += TableCSVExporter.parseCell(row.children[i]);
                        }
        
                        line += (i !== (numCols - 1)) ? "," : "";
                    }
        
                    lines.push(line);
                }
        
                return lines.join("\n");
            }
        
            static parseCell(tableCell) {
                let parsedValue = tableCell.textContent;        
                
                parsedValue = /[",\n]/.test(parsedValue) ? `"${parsedValue}"` : parsedValue;
                return parsedValue;
            }
            
        }
       
    </script>


</body>

</html>

)=====";
