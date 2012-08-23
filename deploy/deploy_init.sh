#!/bin/bash

. constants.sh

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
if [ ! -e "$configfile" ]; then
    cp "$configfile" "$settingsdir"
fi

# Create the service script
############################################
echo "#!/bin/bash" > "$service"
chmod 755 "$service"
echo "" >> "$service"
echo "" >> "$service"
echo ". '$prefix/$installdir/constants.h'" >> "$service"
echo "" >> "$service"
cat agent_service.sh >> "$service"

# Create the service
############################################
#cp "$service" "/etc/init.d/$service"
#chkconfig --add "$service"
# Start the service, and set it to start at boot
############################################
#chkconfig "$service" on


