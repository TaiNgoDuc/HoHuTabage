<?php

    $serverName = "fdb28.awardspace.net";
    $userName = "4230494_postdata";
    $password = "(-oN8:jr2**#Q*,g";
    $dbName = "4230494_postdata";

    $con = new mysqli($serverName, $userName, $password, $dbName);


    if (!empty($_POST['status'])) {
        $status = $_POST['status'];
        $sql = "UPDATE tbl_data SET status ='$status' WHERE id =1";
        $con->query($sql);
    }

?>