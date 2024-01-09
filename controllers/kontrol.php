<?php
require '../koneksi/koneksi.php';

if (isset($_POST['update'])) {
	$id     = $_POST['id'];
	$status = $_POST['status'];

	$sql = "UPDATE kontrol SET status='$status' WHERE id=$id";

	if ($conn->query($sql) === TRUE) {
		$conn->close();

		header('location: /monitoring');
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;

		$conn->close();
		die;
	}
} else if (isset($_GET['getKontrol'])) {
	$sql = "SELECT * FROM kontrol";
	$kontrol = $conn->query($sql);
	$kontrol = mysqli_fetch_assoc($kontrol);

	echo $kontrol['status'];
} else {
	header('location: /monitoring');
}
