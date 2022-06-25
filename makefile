build:
	docker build . -t deli/micromouse

chown:
	sudo chown -R deli:deli .