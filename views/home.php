<?php
require 'koneksi/koneksi.php';

$sql = "SELECT * FROM kontrol";
$kontrol = $conn->query($sql);
$kontrol = mysqli_fetch_assoc($kontrol);

$sql = "SELECT * FROM data ORDER BY createdAt DESC";
$dataSensor = $conn->query($sql);
?>

<div class="row">
	<div class="col-lg-4">
		<form action="controllers/kontrol.php" method="POST">
			<input type="hidden" name="id" value="<?= $kontrol['id']; ?>">
			<div class="form-group">
				<label for="status">Status Relay</label>
				<select name="status" class="form-control">
					<option value="ON" <?= ($kontrol['status'] == 'ON') ? 'selected' : ''; ?>>ON</option>
					<option value="OFF" <?= ($kontrol['status'] == 'OFF') ? 'selected' : ''; ?>>OFF</option>
				</select>
			</div>

			<button type="submit" class="btn btn-primary" name="update">Simpan</button>
		</form>
	</div>
	<div class="col-lg-12 mt-4">
		<div class="d-flex justify-content-between mb-3">
			<h3>Data Sensor</h3>
		</div>

		<!-- Tabel Data Pengguna -->
		<div class="table-responsive">
			<table class="table table-bordered table-striped table-hover">
				<thead>
					<tr>
						<th class="text-center">#</th>
						<th class="text-center">Tanggal</th>
						<th class="text-center">Suhu</th>
						<th class="text-center">Kelembapan</th>
						<th class="text-center">Jarak</th>
						<th class="text-center">Action</th>
					</tr>
				</thead>
				<tbody>
					<?php $i = 1;
					if ($dataSensor->num_rows > 0) : ?>
						<?php while ($row = $dataSensor->fetch_assoc()) : ?>
							<tr>
								<td class="text-center align-middle"><?php echo $i++; ?></td>
								<td class="align-middle text-center"><?php echo $row['createdAt']; ?></td>
								<td class="align-middle text-center"><?php echo $row['suhu']; ?></td>
								<td class="align-middle text-center"><?php echo $row['kelembapan']; ?></td>
								<td class="align-middle text-center"><?php echo $row['jarak']; ?></td>
								<td class="text-center align-middle">
									<div class="btn-group">
										<a href="controllers/data.php?hapus=<?php echo $row['id']; ?>" class="btn btn-danger" onclick="return confirm('Anda yakin data akan dihapus ?')">Hapus</a>
									</div>
								</td>
							</tr>
						<?php endwhile; ?>
					<?php else : ?>
						<tr class="text-center">
							<td colspan='6'>Tidak ada data</td>
						</tr>
					<?php endif; ?>
				</tbody>
			</table>
		</div>
	</div>
</div>


<!-- Modal Tambah Kategori -->
<div class="modal fade" id="tambahKategori" tabindex="-1" role="dialog" aria-labelledby="tambahKategoriModalLabel" aria-hidden="true">
	<div class="modal-dialog" role="document">
		<div class="modal-content">
			<div class="modal-header bg-secondary">
				<h5 class="modal-title" id="tambahKategori">Tambah Kategori</h5>
				<button type="button" class="close" data-dismiss="modal" aria-label="Close">
					<span aria-hidden="true">&times;</span>
				</button>
			</div>
			<form action="controllers/kategori.php" method="POST">
				<div class="modal-body">
					<div class="row">
						<div class="col-lg-12">
							<div class="form-group">
								<label for="nama">Nama Kategori</label>
								<input type="text" class="form-control" name="nama" required autocomplete="off">
							</div>
						</div>
					</div>
				</div>
				<div class="modal-footer">
					<button type="button" class="btn btn-secondary" data-dismiss="modal">Tutup</button>
					<button type="submit" class="btn btn-primary" name="simpan">Simpan</button>
				</div>
			</form>
		</div>
	</div>
</div>
<!-- End Modal Tambah -->