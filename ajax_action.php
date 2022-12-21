<?php

    $serverName = "fdb28.awardspace.net";
    $userName = "4230494_postdata";
    $password = "(-oN8:jr2**#Q*,g";
    $dbName = "4230494_postdata";

    $con = new mysqli($serverName, $userName, $password, $dbName);

    $query_select_status = mysqli_query($con, "SELECT * FROM tbl_data WHERE id = 1");

    if(mysqli_num_rows($query_select_status)){
        while ($rows = mysqli_fetch_array($query_select_status)){
            // if($rows['status'] == "10%"){
            //     echo '<p>Rac 10%</p>';
            // } if($rows['status'] == "20%") {
            //     echo '<p>Rac 20%</p>';
            // } if($rows['status'] == "30%") {
            //     echo '<p>Rac 30%</p>';
            // } if($rows['status'] == "40%") {
            //     echo '<p>Rac 40%</p>';
            // } if($rows['status'] == "50%") {
            //     echo '<p>Rac 50%</p>';
            // }

            $status = $rows['status'];
            echo '<p>Rac'.$status.'</p>
            
        }
    }
    
?>