﻿using CmsTraining.Models.CustomEntities;
using EPiServer.Core;
using EPiServer.PlugIn;

namespace CmsTraining.Models.Properties {
    [PropertyDefinitionTypePlugIn]
    public class StatesListProperty : PropertyList<StateFieldEntry> { }
}