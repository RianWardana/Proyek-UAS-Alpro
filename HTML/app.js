(function() {
    var baseUrl = "http://103.43.44.105/alpro/index.php/app";
    var count = 1;
    var name;

    function sendName() {
    	if (textName.value != "") {
    		name = textName.value
    		textName.value = "";
    		formName.style.display = "none";
    		formMsg.style.display = "block";
    		textMsg.focus();
    	}
    }

    function sendMsg() {
    	if (textMsg.value != "") {
    		var xhttp = new XMLHttpRequest();
    		xhttp.open("POST", `${baseUrl}/send`, true);
			xhttp.send(`${name}: ${textMsg.value}\r\n`);
    		textMsg.value = "";
    	}
    }

    textName.addEventListener('keypress', e => {
    	var key = e.which || e.keyCode;
    	if (key === 13) sendName();
    });

    textMsg.addEventListener('keypress', e => {
    	var key = e.which || e.keyCode;
    	if (key === 13) sendMsg();
    });

    btnSendName.addEventListener('click', e => {sendName()});
    btnSendMsg.addEventListener('click', e => {sendMsg();});

    function loop() {
    	var xhttp;
        xhttp = new XMLHttpRequest();

        xhttp.open("GET", `${baseUrl}/read/${count}`, true);
        xhttp.send();

        xhttp.onreadystatechange = function() {
            if ((xhttp.responseText != 'X') && (xhttp.readyState == 4)) {
                console.log(`Message ${count}-> ${xhttp.responseText}`);
                var oldHTML = container.innerHTML;
                var newHTML = '<p>' + xhttp.responseText + '</p>';
                container.innerHTML = oldHTML + newHTML;
    			container.scrollTop = container.scrollHeight;
                count++;

                setTimeout(function() {
        			loop();
        		}, 100);
            } else if (xhttp.responseText == 'X') {
            	setTimeout(function() {
        			loop();
        		}, 1000);
            }
        };
    } loop();
}())
