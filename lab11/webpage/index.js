window.onload = function() {
    document.getElementById('id_username').onkeydown = function(e) {
        var KEYCODE_0 = 48;
        var KEYCODE_9 = 57;
        return !(e.keyCode >= KEYCODE_0 && e.keyCode <= KEYCODE_9);
    }

    document.getElementById('id_login_form').onsubmit = function(e) {
        console.log(e);
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

        if (document.getElementById('id_password').value.length < 4)
            alert('The password must contain at least 4 characters');
            return false;
        }

        return true;
    }
}
