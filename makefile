build:
	docker build . -t deli/micromouse

chown:
	sudo chown -R deli:deli .

clean:
	sudo rm -rf log install build