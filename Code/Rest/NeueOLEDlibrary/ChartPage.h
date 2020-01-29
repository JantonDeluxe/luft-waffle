const char ChartPage[] = R"=====(
<!doctype html>
<html>

<head>
    <title>Chart - H&ouml;henmesser</title>
    <script src="Chart.min.js"></script>
    <style>
        ul {
            list-style-type: none;
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
            border: none;
            color: white;
            padding: 16px 32px;
            width: 150px;
            text-align: center;
            text-decoration: none;
            display: inline-block;
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
        
        
    </style>
</head>

<body>
    <ul>
        <li><a href="/">Home</a></li>
        <li><a class="active" href="/chart">Vorschau</a></li>
        <li style="float:right"><a href="/about">About</a></li>
    </ul>

    <div style="text-align:left;">
        <h1 style="font-family:verdana;color:white">H&ouml;henmesser</h1>
        <p>
    </div>
    <div class="chart-container" style="position: relative; height:350px; width:100%">
        <canvas id="Chart" width="400" height="400"></canvas>
    </div>

    <form action="/stopp" class="inline">
      <button class="button button2">Stopp</button>
    </form>

    <script>
        var data = [];
        var speed = [];
        var acceleration = [];
        var time = "";

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
                        backgroundColor: 'rgba(123, 219, 48, 0.85)',
                        borderColor: 'rgba(123, 219, 48, 0.85)',
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
            graph.update();
        }

        //Beim Starten der Seite Graphen anzeigen
        window.onload = function() {
            addGraph();
        };

        // Update-Geschwindigkeit (100 ms) NOCHMAL ANPASSEN!
        setInterval(function() {
            getData();
        }, 200);

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
                }
            };
            xhttp.open("GET", "readData", true);
            xhttp.send();
        }
    </script>

</body>

</html>

)=====";
