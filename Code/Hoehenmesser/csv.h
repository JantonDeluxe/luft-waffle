const char CSV_page[] PROGMEM = R"=====(
<!doctype html>
<html>
<head>
  <title>CSV</title> 
</head>	
<body>
	<script>
    var data = [
       ['Foo', 'programmer'],
       ['Bar', 'bus driver'],
       ['Moo', 'Reindeer Hunter']
    ];
     
     
    function download_csv() {
        var csv = 'Name,Title\n';
        data.forEach(function(row) {
                csv += row.join(',');
                csv += "\n";
        });
     
        console.log(csv);
        var hiddenElement = document.createElement('a');
        hiddenElement.href = 'data:text/csv;charset=utf-8,' + encodeURI(csv);
        hiddenElement.target = '_blank';
        hiddenElement.download = 'people.csv';
        hiddenElement.click();
    }
    </script>
     
    <button onclick="download_csv()">Download CSV</button> 
	
	</body>

</html>
)=====";
