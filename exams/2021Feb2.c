    /*
    Escribe un programa servidor UDP que escuche en una dirección (IPv4 o IPv6
    en cualquier formato) y puerto dados como argumentos. Recibirá del cliente una ruta de fichero y le
    devolverá una cadena con el tipo del fichero (regular, directorio, enlace, fifo u otro). Además, al
    recibir cada mensaje imprimirá en el terminal la dirección y el puerto del cliente.
    */
    
    #include <sys/types.h>
    #include <stdio.h>
    #include <sys/stat.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    #include <sys/socket.h>
    #include <netdb.h>

    #define handle_error(msg)\
        do{perror(msg);exit(EXIT_FAILURE);}while(0);
    #define handle_error_gai(e)\
        do{fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(e));exit(EXIT_FAILURE);}while(0);
    #define BUF_SIZE 500

    int
    main(int argc, char *argv[])
    {
        struct addrinfo hints;
        struct addrinfo *rp;
        int sfd, s;
        struct sockaddr_storage addr;
        socklen_t addrlen;
        ssize_t nread;
        char in[BUF_SIZE],out[BUF_SIZE];
        char host[NI_MAXHOST], service[NI_MAXSERV];


        if (argc != 3) {
            fprintf(stderr, "Usage: %s ip port\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
        hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */

        if((s = getaddrinfo(argv[1], argv[2], &hints, &rp)) == -1)  handle_error_gai(s);

        if((sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol)) == -1) handle_error("error in socket");

        if(bind(sfd, rp->ai_addr, rp->ai_addrlen) == -1)handle_error("error in bind");

        freeaddrinfo(rp);           /* No longer needed */

        addrlen=sizeof(addr);

        while(1){
            printf("Esperando conexiones UDP...\n");

            if((nread = recvfrom(sfd, in, BUF_SIZE, 0, (struct sockaddr *) &addr, &addrlen)) == -1) handle_error("Error in recvfrom");
            
            if((s = getnameinfo((struct sockaddr *) &addr, addrlen, host, NI_MAXHOST, service, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV))!=0) handle_error_gai(s);
            
            printf("Received msg from %s:%s\n", host, service);
        
            in[nread-1]='\0';
            struct stat inode;
            if(stat(in,&inode) == -1) handle_error("Error in stat()");
            mode_t mode = inode.st_mode;
            char *file_type;
            if (S_ISLNK(mode)){
                file_type="Symbolic link\n";
            } else if (S_ISREG(mode)) {
                file_type="Regular file\n";
            } else if (S_ISDIR(mode)) {
                file_type="Directory\n";
            } else {
                file_type="Other";
            }
            sprintf(out,"File type: %s",file_type);            

            if (sendto(sfd, out, strlen(out), 0,(struct sockaddr *) &addr, addrlen) == -1) handle_error("Error in sendto");
        }
        return 0;
    }