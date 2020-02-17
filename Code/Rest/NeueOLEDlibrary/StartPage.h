const char StartPage[] = R"=====(

<!DOCTYPE html>
<html>
<head>
    <title>Home - H&ouml;henmesser</title>
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
        
        .button {
            border: none;
            box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
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
            display: inline-block;
            margin-right: 5px;
            color: white;
            border-radius: 8px;
            border: 2px solid #4CAF50;
        }
        
        .button1:hover {
            border-radius: 8px;
            display: inline-block;
            margin-right: 5px;
            background-color: white;
            color: black;
            border: 2px solid #4CAF50;
        }
        
        .button2 {
            border-radius: 8px;
            display: inline-block;
            margin-right: 5px;
            background-color: #0080ff;
            color: white;
            border: 2px solid #0080ff;
        }
        
        .button2:hover {
            border-radius: 8px;
            display: inline-block;
            margin-right: 5px;
            background-color: white;
            color: black;
            border: 2px solid #0080ff;
        }
       
    </style>
</head>

<body>
    <ul>
        <li><a class="active" href="/">Home</a></li>
        <li><a href="/chart">Vorschau</a></li>
        <li style="float:right"><a href="/about">About</a></li>
    </ul>

   <h1 style="font-family: Roboto, verdana, sans-serif;font-size:250%;color:black;text-align:left;padding-top:30px;">H&ouml;henmesser</h1>
    
    <p>
        <p>

        <form action="/start" class="inline">
                <button class="button button1">Start</button>
            </form>

            <form action="/calibrate" class="inline">
                <button class="button button2">Kalibrieren</button>
            </form>

</body>

</html>

)=====";
