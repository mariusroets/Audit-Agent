#!/bin/bash

. constants.sh

# Stop the service if it already exists
############################################
service "$service" stop

# Create log directory
############################################
if [ ! -d "$logdir" ]; then
    mkdir "$logdir"
fi
# Create settings directory
############################################
if [ ! -d "$settingsdir" ]; then
    mkdir "$settingsdir"
fi
# Deploy settings file
############################################
configfile=$prefix/$installdir/configfile.cfg
if [ ! -e "$settingsdir/configfile.cfg" ]; then
    cp "$configfile" "$settingsdir"
fi

# Create the service script
############################################
echo "#!/bin/bash" > "$service"
chmod 755 "$service"
echo "" >> "$service"
echo "" >> "$service"
echo ". '$prefix/$installdir/constants.sh'" >> "$service"
echo "" >> "$service"
cat agent_service.sh >> "$service"

# Create the service
############################################
cp "$service" "/etc/init.d/$service"
chkconfig --add "$service"
# Start the service, and set it to start at boot
############################################
service "$service" start
chkconfig "$service" on


