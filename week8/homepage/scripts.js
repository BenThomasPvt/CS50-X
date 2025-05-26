document.addEventListener('DOMContentLoaded', function() {
    var alertButton = document.getElementById('alertButton');
    if (alertButton) {
        alertButton.addEventListener('click', function() {
            alert('Button clicked!');
        });
    }
});
