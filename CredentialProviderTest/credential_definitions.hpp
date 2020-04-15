#pragma once

#include <string>
#include <cstdint>

namespace glasssix
{
    namespace hello
    {
        /// <summary>
        /// The state of a field.
        /// </summary>
        struct credential_field_state
        {
            CREDENTIAL_PROVIDER_FIELD_STATE state;
            CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE interactive_state;
            std::wstring value;

            credential_field_state(CREDENTIAL_PROVIDER_FIELD_STATE state, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE interactive_state) : state{ state }, interactive_state{ interactive_state }
            {
            }

            credential_field_state() : credential_field_state{ CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_NONE }
            {
            }
        };

        /// <summary>
        /// Define all the fields
        /// </summary>
        enum credential_field : uint32_t
        {
            CREDENTIAL_FIELD_LOGO,
            CREDENTIAL_FIELD_STATUS_TEXT,
            CREDENTIAL_FIELD_SUBMIT_BUTTON,
            CREDENTIAL_FIELD_COUNT
        };
    }
}
