cmd_/home/vuhieu/Desktop/CT040120/module_kernel/Module.symvers := sed 's/ko$$/o/' /home/vuhieu/Desktop/CT040120/module_kernel/modules.order | scripts/mod/modpost -m -a  -o /home/vuhieu/Desktop/CT040120/module_kernel/Module.symvers -e -i Module.symvers   -T -