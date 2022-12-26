$(document).ready(function(){

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
                    if (data >= 90) {
                        alert('Rac day roi do di em oi');
                    }
                }
            }
        })
    }

    $('#status-btn').click(function(){
        fetch_data();
    });
})