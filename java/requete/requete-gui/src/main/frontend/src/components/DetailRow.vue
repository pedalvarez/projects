<template>
  <div>
    <div class="inline field">
      <label>Id: </label>
      <span>{{rowData.id}}</span>
    </div>
    <div class="inline field">
      <label>Short Text: </label>
      <span>{{rowData.shortText}}</span>
    </div>
    <div class="inline field">
      <label>Status: </label>
      <span>{{rowData.status}}</span>
    </div>
    <div class="inline field">
      <label>Given: </label>
      <span>{{rowData.given}}</span>
    </div>
    <div class="inline field">
      <label>When: </label>
      <span>{{rowData.when}}</span>
    </div>
    <div class="inline field">
      <label>Then: </label>
      <span>{{rowData.then}}</span>
    </div>
    <div class="inline field">
      <label>Text: </label>
      <span>{{rowData.text}}</span>
    </div>
  </div>
</template>

<script>
  export default {
    props: {
      rowData: {
        type: Object,
        required: true
      },
      rowIndex: {
        type: Number
      }
    },
    methods: {
      onClick (event) {
      }
    }
  }
</script>
