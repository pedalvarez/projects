<template>
  <div>
    <div class="row">
      <div class="col-md-2">
        <form role="form">
          <div class="form-group">
            <label>Source
              <typeahead
                :maxLength="8"
                async="req/suggest/sources?limit=8&prefix="
                v-model="filterParams.source"
                v-on:typeahead:load-error="onLoadError('Error retrieving source suggestions')"
              ></typeahead>
            </label>
          </div>
        </form>
      </div>
      <div class="col-md-2">
        <form role="form">
          <div class="form-group">
            <label>Status
              <select class="form-control" v-model="filterParams.status">
              <option value=""></option>
              <option value="ENTERED">ENTERED</option>
              <option value="REVIEWED">REVIEWED</option>
              <option value="READY">READY</option>
            </select>
            </label>
          </div>
        </form>
      </div>
      <div class="col-md-2">
        <form role="form">
          <div class="form-group">
            <label>Short Text
              <typeahead
                :maxLength="32"
                async="req/suggest/shortTexts?limit=8&prefix="
                v-model="filterParams.shortText"
                v-on:typeahead:load-error="onLoadError('Error retrieving action suggestions')"
              ></typeahead>
            </label>
          </div>
        </form>
      </div>
    </div>


    <div class="row">
      <div class="col-md-9">
      </div>
      <div class="col-md-3">
        <div class="btn-group">
          <button class="btn btn-default" type="button" @click="resetFilter">
            <em class="glyphicon glyphicon-remove"></em> Clear
          </button>
          <button class="btn btn-default" type="button" @click="doFilter">
            <em class="glyphicon glyphicon-filter"></em> Filter
          </button>
        </div>
      </div>
    </div>

    </div>
</template>

<script>
  import _ from 'underscore'
  import Alert from 'ext/vue-strap/Alert'
  import Datepicker from 'ext/vue-strap/Datepicker'
  import Typeahead from 'ext/vue-strap/Typeahead'
  import VsSelect from 'ext/vue-strap/Select'
  import VsOption from 'ext/vue-strap/Option'
  import {EventBus} from 'eventbus'

  export default {
    components: {
      Alert,
      Datepicker,
      Typeahead,
      VsSelect,
      VsOption
    },
    data () {
      return {
        filterParams: initFilterParams()
      }
    },
    methods: {
      doFilter () {
        this.$emit('filter-set', transformParams(this.filterParams))
      },
      resetFilter () {
        console.log('Resetting')
        this.filterParams = initFilterParams()
      },
      onLoadError (msg) {
        console.log('Typeahead load error!')
        EventBus.$emit('toast-error', msg)
      }
    }
  }

  const initFilterParams = function () {
    return {
      source: '',
      shortText: '',
      status: ''
    }
  }

  const transformParams = function (params) {
    // Clear empty properties
    const transformedParams = _.omit(params, _.isEmpty)

    return transformedParams
  }

</script>
