PREFIX  ?= usr/local
WIFI_PREFIX = /etc
HOSTAPD_PREFIX = /etc/hostapd
TARGETS = hostapd hostapd_cli
DRIVER = 8723au.ko
DRIVER_PATH = /lib/modules/3.0.36+/kernel/drivers/net/wireless/rtl8723au_lwfinger
WIFI_SCRIPT = auto_wifi.sh
HOSTAPD = hostapd.conf

Q=@

all: install

install: $(TARGETS) $(DRIVER) $(WIFI_SCRIPT)
	$(Q)./pre_works.sh
	install -d -m 0755 $(DESTDIR)/$(PREFIX)/bin
	install -m 0755 $(TARGETS) $(DESTDIR)/$(PREFIX)/bin
	rm -rf $(DRIVER_PATH)/$(DRIVER)
	cp $(DRIVER) $(DRIVER_PATH)

uninstall:
	cd $(DESTDIR)/$(PREFIX)/bin && rm -f $(TARGETS) && cd - > /dev/null
	$(Q)./uninstall.sh

clean: uninstall
