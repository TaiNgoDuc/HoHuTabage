<?php

    $serverName = "fdb28.awardspace.net";
    $userName = "4230494_postdata";
    $password = "(-oN8:jr2**#Q*,g";
    $dbName = "4230494_postdata";

    $trashHigh = 24;

    $con = new mysqli($serverName, $userName, $password, $dbName);

    $query_select_status = mysqli_query($con, "SELECT * FROM tbl_data WHERE id = 1");

    if(mysqli_num_rows($query_select_status)){
        while ($rows = mysqli_fetch_array($query_select_status)){
            $status = $rows['status'];
            $trashLevel = $trashHigh - $status;
            $trashLevelPercent = round(($trashLevel / $trashHigh) * 100);
            echo '<span>Trash Level ' . $trashLevelPercent . '%</span>';
            echo '<div class="progress-bar progress-bar-striped progress-bar-animated" role="progressbar" aria-valuenow="' . $trashLevelPercent . '" aria-valuemin="0" aria-valuemax="100" style="width: ' . $trashLevelPercent . '%">' . $trashLevelPercent . '%</div>';
        }
    }
    
?>