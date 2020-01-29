const char AboutPage[] = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <title>About - H&ouml;henmesser</title>
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
        
        div{font-family:Algerian;}
       
    </style>
  </head>
  <body>
    <ul>
      <li>
        <a class= href="/">Home</a>
      </li>
      <li>
        <a href="/chart">Vorschau</a>
      </li>
      <li style="float:right">
        <a class="active" href="/about">About</a>
      </li>
    </ul>
    <h1style="font-family:verdana;font-size:250%;color:white;text-align:left;">I bims 1 Platzhalter!
    </h1>
    <h2 style="font-family:verdana;font-size:250%;color:black;text-align:left;">About</h2>
    <p>
      <div style="font-family:verdana;text-align:left;">
        <h3>H&ouml;henmesser 2.0</h3>
        <p>
          <b>Projektseite:</b>
          <br>
            <a href="https://jantondeluxe.github.io">JantonDeluxe.GitHub.io</a>
          </p>
          <br>
          <p>
            <b>Hardware:</b>
            <br>
            Board: WEMOS D1 mini pro V1.0
              <br>
              Altimeter: Bosch BMP180
                <br>
                 Display: GM009605 OLED
                  <br>
                  D1 mini Data logger shield mit DS1307 RTC
                  </p>
                  <br>
                  <p>
                    <b>Disclaimer:</b>
                    <br>
                    Basiert teilweise auf dem Sketch BMP180_altitude_example aus der SFE_BMP180-Library:
                      <br>
                       V10 Mike Grusin, SparkFun Electronics 10/24/2013
                        <br>
                        V1.1.2 Updates for Arduino 1.6.4 5/2015
                        </p>
                        <p>Basiert teilweise auf dem Tutorial "ESP8266 data logging with real time graphs" auf
    
                          <a href="https://circuits4you.com/2019/01/11/esp8266-data-logging-with-real-time-graphs/">Circuits4you.com</a>
                        </p>
                        <p>Danke an Nick Lamprecht f&uuml;r die Hilfe mit Java Script!</p>
      </div>
   </body>
 </html>

)=====";
