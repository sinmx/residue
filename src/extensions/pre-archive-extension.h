//
//  pre-archive-extension.h
//  Residue
//
//  Copyright 2017-present Muflihun Labs
//
//  Author: @abumusamq
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef PreArchiveExtension_h
#define PreArchiveExtension_h

#include <string>
#include <map>
#include "extensions/extension.h"

namespace residue {

///
/// \brief Base class for any extension that needs to execute a code
/// just before we are about to create .tar.gz
///
/// If as a result of execution, Extension::Result::continueProcess is
/// false the server will not continue with archiving the log (hence
/// PostArchiveExtension will also not be executed)
///
class PreArchiveExtension : public Extension
{
public:
    ///
    /// \brief With each execution pointer to this data is passed in
    /// to take advantage of it
    ///
    struct Data
    {
        ///
        /// \brief Logger ID for which this archive will be created
        ///
        std::string loggerId;

        ///
        /// \brief Archive name that will be created (or should be created) after
        /// resolving all the necessary format specifiers
        ///
        std::string archiveFilename;

        ///
        /// \brief Map of files in the archive
        ///
        std::map<std::string, std::string> files;
    };

    explicit PreArchiveExtension(const std::string& id);

    virtual Extension::Result execute(const Data* const) = 0;
private:
    virtual Extension::Result executeWrapper(void* d) override;
};
}

#endif /* PreArchiveExtension_h */
