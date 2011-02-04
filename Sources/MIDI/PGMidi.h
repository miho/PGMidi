//
//  PGMidi.h
//  MidiMonitor
//
//  Created by Pete Goodliffe on 10/12/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMIDI/CoreMIDI.h>

@class PGMidi;

/// Delegate protocol for PGMidi class.
/// Adopt this protocol in your object to receive events from MIDI
///
/// IMPORTANT NOTE:
/// MIDI input is received from a high priority background thread
@protocol PGMidiDelegate

// Raised on main run loop
- (void) midi:(PGMidi*)midi event:(NSString*)event;

/// NOTE: Raised on high-priority background thread.
///
/// To do anything UI-ish, you must forward the event to the main runloop
/// (e.g. use performSelectorOnMainThread:withObject:waitUntilDone:)
- (void) midi:(PGMidi*)midi midiReceived:(const MIDIPacketList *)packetList;

@end

/// Class for receiving MIDI I/O to/from any MIDI device.
///
/// If you intend your app to support iOS 3.x which does not have CoreMIDI
/// support, weak link to the CoreMIDI framework, and only create a
/// PGMidi object if you are running the right version of iOS.
@interface PGMidi : NSObject
{
    MIDIClientRef           client;
    MIDIPortRef             outputPort;
    MIDIPortRef             inputPort;
    NSUInteger              numberOfConnectedDevices;
    id<PGMidiDelegate> delegate;
}

@property (nonatomic,assign)   id<PGMidiDelegate> delegate;
@property (nonatomic,readonly) NSUInteger              numberOfConnectedDevices;

/// Enables or disables CoreMIDI network connections
- (void) enableNetwork:(BOOL)enabled;

/// Send a MIDI byte stream to every connected MIDI port
- (void) sendMidi:(const UInt8*)bytes size:(UInt32)size;

@end

/// Dump a list of MIDI interfaces as events on this delegate.
///
/// A helpful diagnostic, and an example of how to enumerate devices
NSUInteger ListInterfaces(id<PGMidiDelegate> delegate);