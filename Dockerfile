# Use a basic Debian image with build tools
FROM debian:bullseye-slim

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    clang \
    make \
    git \
    openssh-server \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set up SSH server and create a user for SSH login
RUN mkdir /var/run/sshd
RUN useradd -m dockeruser && echo "dockeruser:Timo" | chpasswd
RUN chmod 777 /home/dockeruser

# Expose SSH port
EXPOSE 22

# Start SSH service when the container starts
CMD ["/usr/sbin/sshd", "-D"]


# Copy the project files into the container
COPY . /app/

# Set working directory
WORKDIR /app
