window.onload = function() {
    document.getElementById('id_username').onkeydown = function(e) {
        var KEYCODE_0 = 48;
        var KEYCODE_9 = 57;
        return !(e.keyCode >= KEYCODE_0 && e.keyCode <= KEYCODE_9);
    }

    function replace_text(elem, text) {
        while(elem.childNodes.length >= 1) {
            elem.removeChild(elem.firstChild);
        }
        elem.appendChild(elem.ownerDocument.createTextNode(text));
    }

    function showHint(str) {
        var xmlhttp;
        if (str.length === 0) {
            document.getElementById("txtHint").innerHTML = "";
            return;
        }
        if (window.XMLHttpRequest){ // IE7+,Firefox,Chrome,Opera, Safari
            xmlhttp = new XMLHttpRequest();
        }
        else{ // code for IE6, IE5
            xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
        }
        xmlhttp.onreadystatechange = function() {
            if (xmlhttp.readyState == 4 && xmlhttp.status === 200){
                document.getElementById("txtHint").innerHTML = xmlhttp.responseText;
            }
        }
        xmlhttp.open("GET","http://www.cs.bgu.ac.il/~abedas/remote_service.php?q="+str, true);
        xmlhttp.send();
    }

    document.getElementById('id_username').onkeyup = function(e) {
        showHint(document.getElementById('id_username').value);
    }

    document.getElementById('id_login_form').onsubmit = function(e) {
        function field_nonempty(id, name) {
            if (document.getElementById(id).value.length === 0) {
                alert('You must enter a ' + name);
                return true;
            }
            return false;
        }

        if (field_nonempty('id_username', 'username')) {
            return false;
        }
        if (field_nonempty('id_password', 'password')) {
            return false;
        }

        if (!document.getElementById('id_password').value[0].match(/[a-zA-Z]/)) {
            alert('The password must begin with a letter');
            return false;
        }

        if (document.getElementById('id_password').value.length < 4) {
            alert('The password must contain at least 4 characters');
            return false;
        }

        replace_text(document.getElementById('id_user_text'), 'You are logged in as ' + document.getElementById('id_username').value);

        return false;
    }
}
