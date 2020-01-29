const char StartPage[]  = R"=====(

<!DOCTYPE html>
<html>

<head>
    <title>Home - H&ouml;henmesser</title>
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
        
        .button1 {
            background-color: #4CAF50;
            color: white;
            border-radius: 8px;
            border: 2px solid #4CAF50;
        }
        
        .button1:hover {
            border-radius: 8px;
            background-color: white;
            color: black;
            border: 2px solid #4CAF50;
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
        <li><a class="active" href="/">Home</a></li>
        <li><a href="/chart">Vorschau</a></li>
        <li style="float:right"><a href="/about">About</a></li>
    </ul>

    <h2style="font-family:verdana;font-size:250%;color:white;text-align:left;">I bims 1 Platzhalter!</h2>
    <h3 style="font-family:verdana;font-size:250%;color:black;text-align:left;">H&ouml;henmesser</h3>
    <p>
        <p>

        <form action="/start" class="inline">
                <button class="button button1">Start</button>
            </form>

            <form action="/stopp" class="inline">
                <button class="button button2">Stopp</button>
            </form>

</body>

</html>

)=====";
