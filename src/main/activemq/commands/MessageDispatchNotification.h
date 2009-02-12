/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _ACTIVEMQ_COMMANDS_MESSAGEDISPATCHNOTIFICATION_H_
#define _ACTIVEMQ_COMMANDS_MESSAGEDISPATCHNOTIFICATION_H_

// Turn off warning message for ignored exception specification
#ifdef _MSC_VER
#pragma warning( disable : 4290 )
#endif

#include <activemq/util/Config.h>
#include <activemq/commands/BaseCommand.h>
#include <decaf/lang/Pointer.h>
#include <activemq/commands/MessageId.h>
#include <activemq/commands/ConsumerId.h>
#include <activemq/commands/ActiveMQDestination.h>
#include <vector>
#include <string>

namespace activemq{
namespace commands{

    /*
     *
     *  Command and marshaling code for OpenWire format for MessageDispatchNotification
     *
     *
     *  NOTE!: This file is auto generated - do not modify!
     *         if you need to make a change, please see the Java Classes
     *         in the activemq-openwire-generator module
     *
     */
    class AMQCPP_API MessageDispatchNotification : public BaseCommand {
    protected:

        decaf::lang::Pointer<ConsumerId> consumerId;
        decaf::lang::Pointer<ActiveMQDestination> destination;
        long long deliverySequenceId;
        decaf::lang::Pointer<MessageId> messageId;

    protected:

        MessageDispatchNotification( const MessageDispatchNotification& other );
        MessageDispatchNotification& operator= ( const MessageDispatchNotification& other );

    public:

        const static unsigned char ID_MESSAGEDISPATCHNOTIFICATION = 90;

    public:

        MessageDispatchNotification();
        virtual ~MessageDispatchNotification();

        /**
         * Get the unique identifier that this object and its own
         * Marshaler share.
         * @returns new DataStructure type copy.
         */
        virtual unsigned char getDataStructureType() const;

        /**
         * Clone this object and return a new instance that the
         * caller now owns, this will be an exact copy of this one
         * @returns new copy of this object.
         */
        virtual MessageDispatchNotification* cloneDataStructure() const;

        /**
         * Copy the contents of the passed object into this object's
         * members, overwriting any existing data.
         * @param src - Source Object
         */
        virtual void copyDataStructure( const DataStructure* src );

        /**
         * Returns a string containing the information for this DataStructure
         * such as its type and value of its elements.
         * @return formatted string useful for debugging.
         */
        virtual std::string toString() const;

        /**
         * Compares the DataStructure passed in to this one, and returns if
         * they are equivalent.  Equivalent here means that they are of the
         * same type, and that each element of the objects are the same.
         * @returns true if DataStructure's are Equal.
         */
        virtual bool equals( const DataStructure* value ) const;

        /**
         * @return an answer of true to the isMessageDispatchNotification() query.
         */
        virtual bool isMessageDispatchNotification() const {
            return true;
        }

        /**
         * Allows a Visitor to visit this command and return a response to the
         * command based on the command type being visited.  The command will call
         * the proper processXXX method in the visitor.
         * 
         * @return a Response to the visitor being called or NULL if no response.
         */
        virtual decaf::lang::Pointer<commands::Command> visit( activemq::state::CommandVisitor* visitor )
            throw( exceptions::ActiveMQException );

        virtual const decaf::lang::Pointer<ConsumerId>& getConsumerId() const;
        virtual decaf::lang::Pointer<ConsumerId>& getConsumerId();
        virtual void setConsumerId( const decaf::lang::Pointer<ConsumerId>& consumerId );

        virtual const decaf::lang::Pointer<ActiveMQDestination>& getDestination() const;
        virtual decaf::lang::Pointer<ActiveMQDestination>& getDestination();
        virtual void setDestination( const decaf::lang::Pointer<ActiveMQDestination>& destination );

        virtual long long getDeliverySequenceId() const;
        virtual void setDeliverySequenceId( long long deliverySequenceId );

        virtual const decaf::lang::Pointer<MessageId>& getMessageId() const;
        virtual decaf::lang::Pointer<MessageId>& getMessageId();
        virtual void setMessageId( const decaf::lang::Pointer<MessageId>& messageId );

    };

}}

#endif /*_ACTIVEMQ_COMMANDS_MESSAGEDISPATCHNOTIFICATION_H_*/
