const char AboutPage[] = R"=====(

<!DOCTYPE html>
<html>
  <head>
    <title>About - H&ouml;henmesser</title>
   
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
        
        div{font-family:Algerian;}
       
    </style>
  </head>
  <body>
    <ul>
      
       <li><a href="/">Home</a></li>
      
      <li>
        <a href="/chart">Vorschau</a>
      </li>
      <li style="float:right">
        <a class="active" href="/about">About</a>
      </li>
    </ul>
    
    <h1 style="font-family:verdana;font-size:250%;color:black;text-align:left;padding-top:30px;">H&ouml;henmesser 2.0</h1>
    <p>
      <div style="font-family:verdana;text-align:left;">
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
                        <p>Basiert teilweise auf dem Tutorial "How to export an HTML table to a CSV file in JavaScript - Project Video" von dcode. Zu finden auf 
    
                          <a href="https://www.youtube.com/watch?v=cpHCv3gbPuk">YouTube</a>
                        </p>
                        <p>Eine große Hilfe waren ebenfalls die vielen HTML- und CSS-Tutorials von 
    
                          <a href="https://www.w3schools.com/">W3schools.com</a>
                        </p>
                        <p>Danke an Nick Lamprecht f&uuml;r die Hilfe mit Java Script!</p>
      </div>
   </body>
 </html>

)=====";
