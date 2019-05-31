# Setup

LBB-libc has only been tested on a "Ubuntu 18.04.2 LTS" host.
For instructions on downloading Ubuntu please visit
[here](https://www.ubuntu.com/download/desktop).

It's possible to run the host as a virtual machine, as long as your hypervisor supports
nested virtualization. 

If you are a Hyper-V user, you can enable nested virtualization with:

```
PS C:\> Set-VMProcessor "Ubuntu 18.04.2 LTS" -ExposeVirtualizationExtensions $TRUE
PS C:\>
```

## Virtualbox

The host must be configured with Oracle Virtualbox and its latest Extension Pack.
For instructions on downloading Virtualbox please visit
[here](https://www.virtualbox.org/wiki/Downloads).

## Clone littleblackbook-libc

To download the LBB-libc project you can clone it from github like so:

```
daniel@LBB-libc:~$ git clone https://github.com/danielhodson/littleblackbook-libc.git
```

## Ansible

The host must have ansible installed.
The following commands can be used to install the latest available version:

```shell
#!/bin/sh

sudo apt-get update
sudo apt-get install -y software-properties-common
sudo apt-add-repository --yes --update ppa:ansible/ansible
sudo apt-get update
sudo apt-get install -y ansible
```

To install the required roles for LBB-libc you can run the following commands:

```shell
#!/bin/sh
cd littleblackbook-libc
cd ansible
ansible-galaxy install -r ./requirements.yml
```

## Vagrant

The host must have vagrant installed.
A helper playbook is available to download and install this for you:

```shell
#!/bin/sh
cd littleblackbook-libc
cd ansible
ansible-playbook ./playbooks/host-install-vagrant.yml
```

## Audit repos

This is optional, but if you would like to clone the libc repositories into `~/audit` on
your host, you can use a helper playbook:

```
#!/bin/sh
cd littleblackbook-libc
cd ansible
ansible-playbook ./playbooks/host-install-repos.yml
```

# Usage

## Start Target(s)

At this point, you probably want to create virtual machines that you can connect into for
testing.
You can do that with the following command:

```
daniel@LBB-libc:~/littleblackbook-libc$ vagrant up
```

This will automatically run the ansible provisioning scripts to install libc and dependant
tooling.
If you ever need to re-provision these packages you can do so with:

```
daniel@LBB-libc:~/littleblackbook-libc$ vagrant up --provision
```

## Connect to Target

Once you have created your guest virtual machines, you can connect into them over ssh and
use as you would a normal system:

```
daniel@LBB-libc:~/littleblackbook-libc$ vagrant ssh diet
```