<?php
require '../koneksi/koneksi.php';

if (isset($_GET['simpan'])) {
	$suhu       = $_GET['suhu'];
	$kelembapan = $_GET['kelembapan'];
	$jarak      = $_GET['jarak'];

	$sql = "INSERT INTO data (suhu, kelembapan, jarak) VALUES ('$suhu', '$kelembapan', '$jarak')";

	if ($conn->query($sql) === TRUE) {
		$conn->close();

		echo 'Berhasil kirim data sensor';
	} else {
		$conn->close();

		echo "Error: " . $sql . "<br>" . $conn->error;
	}
} else if (isset($_GET['hapus'])) {
	$id = $_GET['hapus'];

	$sql = "DELETE FROM data WHERE id=$id";

	if ($conn->query($sql) === TRUE) {
		$conn->close();

		header('location: /monitoring');
	} else {
		echo "Error: " . $sql . "<br>" . $conn->error;

		$conn->close();
		die;
	}
} else {
	header('location: /monitoring');
}
