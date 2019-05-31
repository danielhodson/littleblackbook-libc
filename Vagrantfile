Vagrant.configure("2") do |config|
  # common vm config
  config.vm.box = "ubuntu/bionic64"
  config.vm.provider "virtualbox" do |v|
    v.linked_clone = true
    v.memory = 2048
    v.cpus = 2
  end

  # common vm install python so ansible works
  config.vm.provision "shell", inline: "sudo apt-get update && apt-get install -y python"
  # common vm provisioning
  config.vm.provision "ansible" do |ansible|
    ansible.config_file = "ansible/ansible.cfg"
    ansible.playbook = "ansible/playbooks/guest-common.yml"
  end

  # diet libc vm config
  config.vm.define "diet" do |diet|
    diet.vm.hostname = "diet-linux"
    diet.vm.provision "ansible" do |ansible|
      ansible.config_file = "ansible/ansible.cfg"
      ansible.playbook = "ansible/playbooks/libc-diet.yml"
    end
  end

  # libbsd libc vm config
  config.vm.define "libbsd" do |libbsd|
    libbsd.vm.hostname = "libbsd-linux"
    libbsd.vm.provision "ansible" do |ansible|
      ansible.config_file = "ansible/ansible.cfg"
      ansible.playbook = "ansible/playbooks/libc-libbsd.yml"
    end
  end

  # musl libc vm config
  config.vm.define "musl" do |musl|
    musl.vm.hostname = "musl-linux"
    musl.vm.provision "ansible" do |ansible|
      ansible.config_file = "ansible/ansible.cfg"
      ansible.playbook = "ansible/playbooks/libc-musl.yml"
    end
  end

  # openBSD libc vm config
  config.vm.define "obsd" do |obsd|
    obsd.vm.box = "openbsd/openbsd-6.4"
    obsd.vm.hostname = "obsd"
  end

  # freeBSD libc vm config
  config.vm.define "fbsd" do |fbsd|
    fbsd.vm.box = "freebsd/FreeBSD-12.0-STABLE"
    fbsd.vm.hostname = "fbsd"
  end

end
