(function() {
    var baseUrl = "http://103.43.44.105/alpro/index.php/app/read/";
    var count = 1;
    setInterval(function() {
        var xhttp;
        xhttp = new XMLHttpRequest();

        xhttp.open("GET", `${baseUrl}${count}`, true);
        xhttp.send();

        setTimeout(function() {
            if (xhttp.responseText != 'X') {
                console.log(xhttp.responseText);
                var oldHTML = container.innerHTML;
                var newHTML = '<p>' + xhttp.responseText + '</p>';
                container.innerHTML = oldHTML + newHTML;
                count++;
            }
        }, 100);
    }, 1000);
}())
