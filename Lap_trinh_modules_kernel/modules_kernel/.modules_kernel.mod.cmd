cmd_/home/vuhieu/Desktop/CT040120/modules_kernel/modules_kernel.mod := printf '%s\n'   modules_kernel.o | awk '!x[$$0]++ { print("/home/vuhieu/Desktop/CT040120/modules_kernel/"$$0) }' > /home/vuhieu/Desktop/CT040120/modules_kernel/modules_kernel.mod