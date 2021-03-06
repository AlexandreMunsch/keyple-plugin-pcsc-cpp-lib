/**************************************************************************************************
 * Copyright (c) 2021 Calypso Networks Association https://calypsonet.org/                        *
 *                                                                                                *
 * See the NOTICE file(s) distributed with this work for additional information regarding         *
 * copyright ownership.                                                                           *
 *                                                                                                *
 * This program and the accompanying materials are made available under the terms of the Eclipse  *
 * Public License 2.0 which is available at http://www.eclipse.org/legal/epl-2.0                  *
 *                                                                                                *
 * SPDX-License-Identifier: EPL-2.0                                                               *
 **************************************************************************************************/

#pragma once

#include <map>
#include <memory>
#include <string>

/* Keyple Plugin Pcsc */
#include "PcscPluginFactory.h"

namespace keyple {
namespace plugin {
namespace pcsc {

/**
 * Builds instances of {@link PcscPluginFactory} from values configured by the setters.
 *
 * <p>The Builder checks if a value configured by a setter satisfies the syntax requirements defined
 * by the {@link PcscPluginFactoryAdapter} class.
 *
 * <p>The following example shows how to create a PcscPluginFactory object with the
 * PcscPluginFactoryBuilder.
 *
 * <pre>{@code
 * PcscPluginFactory pcscPluginFactory = new PcscPluginFactoryBuilder()
 *      .useContactReaderIdentificationFilter(".*(Cherry TC|Identive).*")
 *      .useContactlessReaderIdentificationFilter(".*(ASK LoGO|ACS ACR122).*")
 *      .updateProtocolIdentificationRule(PcscSupportedContactlessProtocol).ISO_14443_4("3B8B80.*")
 *      .updateProtocolIdentificationRule(PcscSupportedContactlessProtocol)
 *          .INNOVATRON_B_PRIME_CARD("3B8F8001805A0.*")
 *      .build();
 * }</pre>
 *
 * Note: all setters of this class are optional.<br>
 * It is possible to assign later a protocol type at the reader level using the method {@link
 * PcscReader#setContactless(boolean)}. <br>
 * A set of default protocol identification rules is also proposed.
 *
 * @see PcscSupportedContactProtocol
 * @see PcscSupportedContactlessProtocol
 * @since 2.0.0
 */
class PcscPluginFactoryBuilder final {
public:

    /**
     * Builder to build a {@link PcscPluginFactory}.
     *
     * @since 2.0.0
     */
    class Builder {
    public:
        friend PcscPluginFactoryBuilder;
        
        /**
         * Sets a filter based on regular expressions to make the plugin able to identify a contact
         * reader from its name.
         *
         * <p>Readers whose names match the provided regular expression will be considered contact
         * type readers.
         *
         * <p>For example, the string ".*less.*" could identify all readers having "less" in their
         * name as contactless readers.
         *
         * <p>Names are not always as explicit, so it is sometimes better to test the brand and
         * model.
         * <br>
         * Commonly used contact readers include "Cherry TC" or "Identive".<br>
         * Thus, an application using these readers should call this method with {@code ".*(Cherry
         * TC|Identive).*"} as an argument.
         *
         * @param contactReaderIdentificationFilter A string a regular expression.
         * @return This builder.
         * @throw IllegalArgumentException If the provided string is null or empty.
         * @see #useContactlessReaderIdentificationFilter(String)
         * @since 2.0.0
         */
        Builder& useContactReaderIdentificationFilter(
            const std::string contactReaderIdentificationFilter);

        /**
         * Sets a filter based on regular expressions to make the plugin able to identify a contact
         * reader from its name.
         *
         * <p>Readers whose names match the provided regular expression will be considered
         * contactless type readers.
         *
         * <p>Commonly used contactless readers include the "ASK LoGO" and "ACS ACR 122" models.<br>
         * Thus, an application using these readers should call this method a first time with
         * ".*(ASK LoGO|ACS ACR122).*" as an argument.
         *
         * @param contactlessReaderIdentificationFilter A string a regular expression.
         * @return This builder.
         * @throw IllegalArgumentException If the provided string is null or empty.
         * @see #useContactReaderIdentificationFilter(String)
         * @since 2.0.0
         */
        Builder& useContactlessReaderIdentificationFilter(
            const std::string contactlessReaderIdentificationFilter);

        /**
         * Updates a protocol identification rule.
         *
         * <p>A protocol rule is a regular expression contained in a String.
         *
         * <ul>
         *   <li>If a rule already exists for the provided protocol, it is replaced.
         *   <li>If no rule exists for the provided protocol, it is added.
         *   <li>If the rule is null, the protocol is disabled.
         * </ul>
         *
         * @param readerProtocolName A not empty String.
         * @param protocolRule null to disable the protocol.
         * @return This builder.
         * @throw IllegalArgumentException If one of the argument is null or empty
         * @since 2.0.0
         */
        Builder& updateProtocolIdentificationRule(
            const std::string& readerProtocolName, const std::string& protocolRule);

        /**
         * Returns an instance of PcscPluginFactory created from the fields set on this builder.
         *
         * @return A {@link PcscPluginFactory}
         * @since 2.0.0
         */
        std::shared_ptr<PcscPluginFactory> build();

    private:
        /**
         * 
         */
        std::string mContactReaderIdentificationFilter;
        
        /**
         * 
         */
        std::string mContactlessReaderIdentificationFilter;
        
        /**
         * 
         */
        std::map<std::string, std::string> mProtocolRulesMap;

        /**
         * (private) Constructs an empty Builder. The default value of all strings is null, the
         * default value of the map is an empty map.
         */
        Builder();
    };

    /**
     * Creates builder to build a {@link PcscPluginFactory}.
     *
     * @return created builder
     * @since 2.0.0
     */
    static Builder* builder();

private:
    /**
     * 
     */
    PcscPluginFactoryBuilder() {}
};

}
}
}
