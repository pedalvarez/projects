//------------------------------------------------------------------------------
// <copyright company="Microsoft Corporation">
//      Copyright (c) Microsoft Corporation.  All rights reserved.
// </copyright>
//------------------------------------------------------------------------------

using System;

namespace SQLConfigurator
{
	public interface IDataConnectionUIControl
	{
		void Initialize(IDataConnectionProperties connectionProperties);
		void LoadProperties();
	}
}
