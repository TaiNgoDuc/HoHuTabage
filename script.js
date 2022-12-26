$(document).ready(function(){

    setInterval(function(){
        fetch_data();
    }, 5000)

    function fetch_data(){
        $.ajax({
            url :"ajax_action.php",
            method: "POST",
            success: function(data){
                console.log(data);
                var data = parseInt(data);
                if (data > 0) {
                    $('#progress-bar').attr('value', data);
                    $('#status').text(data + '%');
                    data = Math.round(data / 10) * 10;
                    $('#recycle-bin').attr('src', 'images/' + data + '.png');
                }
            }
        })
    }
})